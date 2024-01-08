# Build an editable version of the Python module.
# shellcheck source=.env
source "${NUMOOP_VENV_SOURCE}"
set -a; source .env; set +a
pip install --no-build-isolation --config-settings=editable.rebuild=true -ve .
