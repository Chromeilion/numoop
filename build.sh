# Build an editable version of the Python module.
# Build in debug mode
export SKBUILD_CMAKE_BUILD_TYPE=Debug
# Use ./build as the build directory
export SKBUILD_BUILD_DIR=build
# Additional logging and higher verbosity
export SKBUILD_CMAKE_VERBOSE=true
export SKBUILD_LOGGING_LEVEL=INFO

set -a; source .env; set +a  # Get config from a .env file
# shellcheck source=.env
source "${NUMOOP_VENV_SOURCE}"  # Activate the virtual environment
pip install --no-build-isolation --config-settings=editable.rebuild=true -ve .
