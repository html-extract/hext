Hext for PHP
============

[Documentation](https://hext.thomastrapp.com/download#hext-for-php)


#### Build instructions

First [build and install Hext](https://hext.thomastrapp.com/download#build-hext-from-source). Then, install php-cli (or php) , php-dev (both version ≥7.0) and swig (version ≥3.0.11).

```sh
# relative to the project root
cd libhext/bindings/php/build
cmake .. && make
```

The Hext PHP extension is comprised of two files: `hext.php` and a shared library called `hext.so`. In typical PHP setups the [dl()](https://www.php.net/manual/en/function.dl.php) function which loads dynamic libraries at runtime is disabled. Therefore in most cases the extension must be loaded at PHP's startup. There are two ways to do this:

* php.ini: Add the line "extension=/path/to/hext.so" to your php.ini file, ideally below the section called "Dynamic Extensions".
* PHP CLI's -d parameter: Run PHP with the argument "-d extension=/path/to/hext.so".

And lastly, PHP needs to be able to find `hext.php`. This file may be anywhere in your [include_path](http://php.net/manual/en/ini.core.php#ini.include-path).
