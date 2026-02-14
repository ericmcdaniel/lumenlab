#!/usr/bin/env bash

set -euo pipefail

echo "Determining next SemVer..."

if [ -z "${GITHUB_TOKEN:-}" ]; then
  echo "GITHUB_TOKEN not set"
  exit 1
fi

OWNER="${GITHUB_REPOSITORY%%/*}"
REPO="${GITHUB_REPOSITORY##*/}"
SHA="${GITHUB_SHA}"

git fetch --tags
LATEST_TAG=$(git tag --list 'v*.*.*' --sort=-v:refname | head -n1 || true)

if [ -z "$LATEST_TAG" ]; then
  LATEST_TAG="v0.0.0"
fi

echo "Latest tag: $LATEST_TAG"

VERSION="${LATEST_TAG#v}"
IFS='.' read -r MAJOR MINOR PATCH <<< "$VERSION"

PRS_JSON=$(curl -s \
  -H "Authorization: Bearer $GITHUB_TOKEN" \
  -H "Accept: application/vnd.github+json" \
  "https://api.github.com/repos/$OWNER/$REPO/commits/$SHA/pulls")

echo "$PRS_JSON" | jq .

PR_COUNT=$(echo "$PRS_JSON" | jq length)

if [ "$PR_COUNT" -eq 0 ]; then
  echo "No PR associated with this commit."
  exit 1
fi

LABELS=$(echo "$PRS_JSON" | jq -r '.[0].labels[].name' | tr '[:upper:]' '[:lower:]')

BUMP="patch"

COUNT=0
for LABEL in major minor patch; do
  if echo "$LABELS" | grep -qx "$LABEL"; then
    BUMP="$LABEL"
    COUNT=$((COUNT+1))
  fi
done

if [ "$COUNT" -gt 1 ]; then
  echo "Multiple SemVer labels applied. Use only one of: major, minor, patch."
  exit 1
fi

echo "Version bump type: $BUMP"

case "$BUMP" in
  major)
    MAJOR=$((MAJOR+1))
    MINOR=0
    PATCH=0
    ;;
  minor)
    MINOR=$((MINOR+1))
    PATCH=0
    ;;
  patch)
    PATCH=$((PATCH+1))
    ;;
esac

NEW_TAG="v${MAJOR}.${MINOR}.${PATCH}"

echo "New tag: $NEW_TAG"

echo "tag=$NEW_TAG" >> "$GITHUB_OUTPUT"
