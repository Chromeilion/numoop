# Build an editable version of the Python module.
# shellcheck source=.env
source "${NUMOOP_VENV_SOURCE}"  # Activate the virtual environment
set -a; source .env; set +a  # Get config from a .env file
pip install --no-build-isolation --config-settings=editable.rebuild=true -ve .
