# Build Instructions

1. Set up [Emscripten](https://emscripten.org) SDK.

   ```sh
   # in libraries/
   ./setup_emsdk.sh

   In file emsdk/upstream/emscripten/emcc.py update the content

   ======================================
   UNSUPPORTED_LLD_FLAGS = {
    # macOS-specific linker flag that libtool (ltmain.sh) will if macOS is detected.
    '-bind_at_load': False,
    '-retain-symbols-file': True,
    # wasm-ld doesn't support soname or other dynamic linking flags (yet).   Ignore them
    # in order to aid build systems that want to pass these flags.
    '-soname': True,
    '-allow-shlib-undefined': False,
    '-rpath': True,
    '-rpath-link': True,
    '-version-script': True,
   }
   ======================================

   source emsdk/emsdk_env.sh
   ```

2. Compile GLPK for Emscripten

   ```sh
   # in libraries/
   ./make_lib.sh em++
   ```

3. Transcompile C++ code into JavaScript code.
   (The core algorithm is written in C/C++ by Min Xie).

   emcmake cmake ..
   emmake make




   ```sh
   # in the project root folder
   make web
   ```

4. Install Yarn.
   [Installation Guide of Yarn](https://yarnpkg.com/lang/en/docs/install/)
   brew install yarn

5. Install dependencies

   ```sh
   # in react-app/
   yarn install
   ```

6. Run the demo

   ```sh
   # in react-app/
   yarn start
   ```

   The demo will be automatically opened in the browser. Follow this [YouTube video](https://www.youtube.com/watch?v=FjFbNcQYDFM) to interact with the demo.

7. Build the demo for deployment
   ```sh
   # in react-app/
   yarn run build
   ```
   The built webpages are placed in the `react-app/build/` folder.
