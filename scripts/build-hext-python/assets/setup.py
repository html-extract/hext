from setuptools import setup, dist
from setuptools.command.install import install
import os


class BinaryDistribution(dist.Distribution):
    def has_ext_modules(foo):
        return True


class PostInstallCommand(install):
    def run(self):
        install.run(self)
        if not os.path.isdir(self.install_scripts):
            os.makedirs(self.install_scripts)
        package_dir = os.path.dirname(os.path.abspath(__file__))
        binary_dir = os.path.join(package_dir, "bin");
        binary = "htmlext"
        source = os.path.join(binary_dir, binary)
        target = os.path.join(self.install_scripts, binary)
        if os.path.isfile(target):
            os.remove(target)
        self.copy_file(source, target)


this_directory = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(this_directory, 'README.md')) as f:
    long_description = f.read()


setup(
    name='hext',
    package_data={'hext': ['_hext.so', 'gumbo.license', 'rapidjson.license']},
    version='0.2.3',
    description="A module and command-line utility to extract structured data from HTML",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url='https://hext.thomastrapp.com/',
    author='Thomas Trapp',
    author_email='hext@thomastrapp.com',
    include_package_data=True,
    distclass=BinaryDistribution,
    cmdclass={'install': PostInstallCommand},
    packages=['hext'],
    classifiers=[
        'Development Status :: 5 - Production/Stable',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: Apache Software License',
        'Operating System :: POSIX :: Linux',
        'Operating System :: MacOS :: MacOS X',
        'Programming Language :: C++',
        'Topic :: Internet :: WWW/HTTP',
        'Topic :: Software Development :: Libraries :: Python Modules',
    ],
    keywords='html-extraction scraping html data-extraction',
    project_urls={
        'Github': 'https://github.com/html-extract/hext/',
        'Bug Reports': 'https://github.com/html-extract/hext/issues',
        'Author': 'https://thomastrapp.com/'
    },
)
