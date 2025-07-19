# config

A humble, simplified `.INI` file parser and configuration system.



## Getting Started

These instructions will get you a copy of the project up and running
on your local machine for development and testing purposes. See
the Installing section for notes on how to deploy the project on a
live system.


### Prerequisites

The code is written using only C standard library functions and so should
work on any system capable of compiling C99 or above.

The configuration and build process are based on a POSIX compliant system
except for a default dependency on `install`, normally provided by GNU coreutils.
This dependency means that the build process should work on any Linux, macOS,
or BSD-derived system.

Additionally, [Criterion](https://github.com/Snaipe/Criterion) is used to provide
unit testing for this project and as such any requirements of that project are
requirements for building and running the unit tests supplied with this project


## Building

### Configuring

Most options for building and installing can be configured in
the [Makefile](Makefile) configuration section. Hopefully this
is straightforward to understand, but otherwise here is a short
guide.

The makefile has a marked section that contains all the settings for the
build process. The configuration section is broken into two subsections.
The first subsection contains a series of settings that control which paths on
the filesystem the build process should interact with:
- `SOURCE_DIR` - The directory that contains the source files.
- `OBJECT_DIR` - The directory to store files needed during compilation.
- `TEST_DIR` - The directory that contains unit tests.
- `INSTALL_DIR` - The directory to install the compilation artefacts to.
- `HEADER_DIR` - The directory to install the header (`.h`) files to.

The second subsection allows you to configure which programs to use, and how to use 
them, for the compilation process:
- `CC` - A C99 or above compatible C compiler. This can be commented out to allow `make` to choose
- `COMPILE_FLAGS` - A list of arguments to pass to `CC` exclusively during the compilation step
- `LINK_FLAGS` - A list of arguments to pass to `CC` exclusively during the linking step
- `TEST_FLAGS` - A list of arguments used when building the test binaries
- `INSTALL` - An `install` compatible program or script
- `INSTALL_FLAGS` - A list of arguments passed to `INSTALL`

The rest of the makefile is for target generation and general utility and can be
left unaltered

### Compiling

After downloading the project, and configuring it to your liking, compilation
should be as easy as running make in the project's root directory:

```shell
$ make
```

### Installing

Installing follows a similar pattern to the compilation process, but requires
superuser privileges in order to install system-wide:

```shell
$ sudo make install
```

The makefile provided also has an uninstallation target which also requires
superuser privileges:

```shell
$ sudo make uninstall
```

## Usage

The interface to this project is designed with ease of use in mind:

```c++
/* simple_example.c */

#include <config.h>
#include <string.h>
#include <unistsd.h>

// Optionally defining the configuration file path as a compile time constant
#define CONFIG_PATH "config.ini"


// Wrapping everything up in a struct for convenience
struct settings {
    int output_fd;
    char* message;
};


// Some function that returns an initialised settings struct
extern struct settings get_default_settings();


// Error checking here has been omitted for brevity
int main() {
    struct settings stngs = get_default_settings();
    
    const config_t* cfg = config_read_file(CONFIG_PATH);
    
    // config_get makes no changes to the final argument if the key isn't found
    config_get(cfg, "output.fd", &stngs.output_fd);
    config_get(cfg, "message", &stngs.message);
    
    write(stngs.output_fd, stngs.message, strlen(stngs.message));
}
```

And the corresponding `.INI` file:

```ini
# simple_example.ini

message = Hello, World!

[output]
# A file descriptor of 1 corresponds to stdout
fd = 1
```


## File Format

This project is built around a simplified and less flexible interpretation of `.INI`
files than may be typical, based around these rules:
1. The file must be processable using a line-by-line method
2. Each line must be one of four types, determined be the first character:
    - Blank line (if the first char is any type of white space or the line contains no characters)
    - Comments (if the line starts with `#`)
    - Section header (if the line starts with `[`)
    - Key-value pair (if the first character is any value not specified above)
3. Comments and blank lines are completely ignored and have no effect
4. All keys under a section header are prefixed with the name of the section header and a period


### Examples

A typical valid file might look like this: 

```ini
version = 0.1

# This is a comment
[user]
name = John Smith
organisation = Unknown

# This is another comment
[details]
server = 127.0.0.1
port = 23
file = /etc/example.ini
```

And may be processed into this series of key-value pairs:

```c++
"version" = 0.1
"user.name" = "John Smith"
"user.organisation" = "Unknown"
"details.server" = "127.0.0.1"
"details.port" = 23
"details.file" = "/etc/example.ini"
```

Note that there is no nesting of keys


## Contributing

Please read
[CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426)
for details on our code of conduct, and the process for submitting
pull requests to us.


## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions
available, see the
[tags on this repository](https://github.com/Melephas/tplate/tags).


## Authors

* **Sam Miller** - *Initial work* -
  [Melephas](https://github.com/Melephas)

See also the list of
[contributors](https://github.com/Melephas/config/graphs/contributors)
who participated in this project.


## License

This project is licensed under the BSD 3-Clause Clear License - see the
[LICENSE](LICENSE) file for details

