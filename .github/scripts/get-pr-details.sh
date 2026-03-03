#!/usr/bin/env bash
set -euo pipefail

if [ -z "${PR_NUMBER:-}" ]; then
  echo "No PR number provided, skipping release notes."
  echo "title=" >> "$GITHUB_OUTPUT"
  echo "body=" >> "$GITHUB_OUTPUT"
  exit 0
fi

PR_JSON=$(gh pr view "$PR_NUMBER" --json title,body)
TITLE=$(echo "$PR_JSON" | jq -r '.title // ""')
BODY=$(echo "$PR_JSON" | jq -r '.body // ""')

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

echo "pr_number=$PR_NUMBER" >> "$GITHUB_OUTPUT"