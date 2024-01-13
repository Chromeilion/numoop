# Build an editable version of the Python module.
# shellcheck source=.env
set -a; source .env; set +a  # Get config from a .env file
source "${NUMOOP_VENV_SOURCE}"  # Activate the virtual environment
pip install --no-build-isolation --config-settings=editable.rebuild=true -ve .
