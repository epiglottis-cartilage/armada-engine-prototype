#!/bin/bash

# other dependencies (except opengl)
REQUIRED_PACKAGES=(
    libglew-dev
    libsdl2-dev
    libsdl2-image-dev
    libglm-dev
)

# check opengl mesa implementation or nvidia driver implementation
function check_opengl_installed() {
    if apt list --installed 2>/dev/null | grep -q "^libgl1-mesa-dev/"; then
        return 0
    elif apt list --installed 2>/dev/null | grep -q "^nvidia-driver/"; then
        return 0
    else
        return 1
    fi
}

# check other dependencies
function check_dependencies() {
    missing=0

    # check OpenGL（mesa or nvidia）
    if ! check_opengl_installed; then
        missing=1
    fi

    # cheeck remaining
    for pkg in "${REQUIRED_PACKAGES[@]}"; do
        if ! apt list --installed 2>/dev/null | grep -q "^$pkg/"; then
            missing=1
            break
        fi
    done

    if [ $missing -eq 0 ]; then
        echo "all dependencies are satisfied"
        exit 0
    else
        echo "missing dependencies: run ./dependency.sh install to install them"
        exit 1
    fi
}

# suggest: use mesa , since widely supported
function install_dependencies() {
    echo "installing dependencies..."
    sudo apt update
    sudo apt install -y libgl1-mesa-dev "${REQUIRED_PACKAGES[@]}"
}

# main entry point
case "$1" in
    check)
        check_dependencies
        ;;
    install)
        install_dependencies
        ;;
    *)
        echo "usage: $0 [check|install]"
        exit 1
        ;;
esac
