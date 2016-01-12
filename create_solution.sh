source "settings/settings.sh"
export REPO_NAME="polynomial.systemc"

./clean.sh
git clone $GITHUB_PREFIX$REPO_NAME".git"

mv $REPO_NAME solution
cp files/* -r solution/
