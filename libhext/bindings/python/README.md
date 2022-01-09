Hext for Python
===============

[Documentation](https://hext.thomastrapp.com/download#hext-for-python)

**Note**: Hext for Python can be installed through pip: `pip install hext`.


#### Build instructions

First [build and install Hext](https://hext.thomastrapp.com/download#build-hext-from-source). Then, install python, python-dev (both version ≥2.7) and swig (version ≥3.0).

```sh
# relative to the project root
cd libhext/bindings/python/build
cmake .. && make
```

The Hext Python extension is comprised of two files: `hext.py` and a shared library called `_hext.so`. Unfortunately, there's no automated way of installing the extension yet, so you'll have to take care of this part yourself.
Running `python -m site` will show you all the locations Python will check in search of an extension. Use the directory given by `python -m site --user-site` to install the extension for the current user only.

```sh
# list all locations where python looks for
# extensions
python -m site
# create the directory where python expects
# user installed extensions (if it doesn't
# exist already)
mkdir --parents $(python -m site --user-site)
# copy both files to this directory
cp hext.py _hext.so \
    $(python -m site --user-site)
```
