Hext for Node
=============

[Documentation](https://hext.thomastrapp.com/download#hext-for-node)

**Note**: Hext for Node can be installed through npm: `npm install hext`.


#### Build instructions

First [build and install Hext](https://hext.thomastrapp.com/download#build-hext-from-source). Then, install nodejs, nodejs-dev (or libnode-dev) and npm.

```sh
# relative to the project root
cd libhext/bindings/nodejs
# install build dependencies
npm install
# build the project
npm run build

# optional: install the extension for local
# projects (requires root)
cd libhext/bindings/nodejs
npm link
# now npm cann pull hext into your projects
cd /path/to/your/project
npm link hext

# alternative: use the path from the repository
cd /path/to/your/project
npm install \
  /path/to/libhext/bindings/nodejs --save
# test loading hext
node -e "require('hext')" && echo "It works!"
```
