Hext for Ruby
=============

[Documentation](https://hext.thomastrapp.com/download#hext-for-ruby)


#### Build instructions

First [build and install Hext](https://hext.thomastrapp.com/download#build-hext-from-source). Then, install ruby, ruby-dev (both version ≥2.1) and swig (version ≥3.0).

```sh
# relative to the project root
cd libhext/bindings/ruby/build
cmake .. && make
```

The Hext Ruby extension consists of a single shared library called `hext.so`. Unfortunately, there's no automated way of installing the extension yet, so you'll have to take care of this part yourself.
Running `ruby -e 'puts $LOAD_PATH'` will show you all the locations Ruby will check in search of an extension. Copying the shared library to any one of these locations should suffice.

```sh
# list all locations where ruby looks for
# extensions
ruby -e 'puts $LOAD_PATH'
# Example: install the extension system wide
# (requires root)
cp hext.so /usr/local/lib/site_ruby
# Alternative: Run ruby with the -I parameter,
# where <path> is the path containing the extension.
ruby -I<path> your-script.rb
```
