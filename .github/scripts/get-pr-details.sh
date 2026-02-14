#!/usr/bin/env bash

set -euo pipefail

echo "Retrieving PR information..."

if [ -z "${GITHUB_TOKEN:-}" ]; then
  echo "GITHUB_TOKEN not set"
  exit 1
fi

OWNER="${GITHUB_REPOSITORY%%/*}"
REPO="${GITHUB_REPOSITORY##*/}"
SHA="${GITHUB_SHA}"

PRS_JSON=$(curl -s \
  -H "Authorization: Bearer $GITHUB_TOKEN" \
  -H "Accept: application/vnd.github+json" \
  "https://api.github.com/repos/$OWNER/$REPO/commits/$SHA/pulls")

PR_COUNT=$(echo "$PRS_JSON" | jq length)

if [ "$PR_COUNT" -eq 0 ]; then
  echo "No PR associated with this commit."
  echo "title=" >> "$GITHUB_OUTPUT"
  echo "body=" >> "$GITHUB_OUTPUT"
  exit 0
fi

TITLE=$(echo "$PRS_JSON" | jq -r '.[0].title // ""')
BODY=$(echo "$PRS_JSON" | jq -r '.[0].body // ""')

{
  echo "title<<EOF"
  echo "$TITLE"
  echo "EOF"
} >> "$GITHUB_OUTPUT"

{
  echo "body<<EOF"
  echo "$BODY"
  echo "EOF"
} >> "$GITHUB_OUTPUT"

echo "PR details captured."
echo "-  Title = $TITLE."
echo "-  Description = $BODY."
