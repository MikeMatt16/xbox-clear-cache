# Xbox Clear Cache
This tool is a simple utility that clears the Xbox cache partitions, built using [nxdk](https://github.com/XboxDev/nxdk).

## Download
To download the built executable, check out [Releases](https://github.com/MikeMatt16/xbox-clear-cache/releases) page.

## Build Instructions
If you'd rather build it from source yourself, follow these steps. Keep in mind that in order to build, you must have all of the [prerequisites](https://github.com/XboxDev/nxdk?tab=readme-ov-file#prerequisites) of nxdk installed, and have a build environment ready.

1. Clone the repository along with its submodules:

        git clone --recurse-submodules https://github.com/MikeMatt16/xbox-clear-cache.git
2. Navigate to the directory of the newly cloned repository.

        cd xbox-clear-cache
3. Run the nxdk activation script, and then build.

        ./deps/nxdk/bin/activate
        make

4. The built executable should be found at `bin/default.xbe`. Alternatively, an ISO containing the program named `clear-cache.iso` should be found in the root directory.
