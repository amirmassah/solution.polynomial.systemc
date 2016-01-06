source "settings/settings.sh"
export REPO_NAME="xor.systemc"

./clean.sh
git clone $GITHUB_PREFIX$REPO_NAME".git"

cp files/* -r $REPO_NAME/

