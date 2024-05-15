# SPK_Utils
A small library of utilities, created for my own purposes. In some parts it's nothing more than a very simple wrapper around other libraries.

## Dependencies
- [SPK_Log](https://www.github.com/thespookman/log)
- libuuid1
- libscrypt
- Catch2 (not required if you skip the tests as described below)

## Build
`$ make all` builds and runs tests.
`$ make build` just builds.

## Install
`# make install`, which by default uses `DESTDIR=/usr`, I recommend setting `DESTDIR` to install somewhere else.

## Usage
The library uses 3 headers
- `spk_utils/error.hpp`
- `spk_utils/hash.hpp`
- `spk_utils/uuid.hpp`
Each header defines its own namespace
- `spk::err`
- `spk::hash`
- `spk::uuid`

### error.hpp
This utility just reduces boilerplate when defining exceptions in C++.

Defines a very simple class `spk::err::Error` which extends `std::exception`. It also defines a macro `SPK_ERR(id, message)`. Calling `SPK_ERR` defines a new class that extends `spk::err::Error`, called `id` and that returns `message` from `what()`.

When the generated class is instantiated, it also uses SPK_Log to write a message to your current log file (if you aren't using SPK_Log other than as a dependency to this, it will write to `log.log`.

### hash.hpp
This utility is merely a simpler API around libscrypt. It can hash text and check whether a string matches an existing hash.

Two functions are defined, that work exactly as you would expect.
- `std::string spk::hash::hash (std::string to_hash)` - can throw `spk::hash::Hash_Failed`.
- `bool        spk::hash::check_hash (std::string to_check, std::string hash)` - can throw `spk::hash::Check_Hash_Failed`.

### uuid.hpp
This utility is an API around libuuid1. It defines a UUID class for more easily managing your UUIDs.

The following static functions are defined:
- `spk::uuid::UUID spk::uuid::create ()` - creates a new, random UUID.
- `spk::uuid::UUID spk::uuid::read (std::string text)` - creates a new UUID from a human-readable string (i.e. `XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX`). Can throw `spk::uuid::UUID_Error`.

The UUID class has two constructors:
- `spk::uuid::UUID()` - creates an 'empty' UUID.
- `spk::uuid::UUID(std::string data)` - creates a UUID containing `data`, which should be a 16-byte string (i.e. not a human-readable UUID). This is useful for reading UUIDs from databases, streams, or anywhere else it makes sense to use binary data. Note that this does not check that `data` is a valid UUID. If this is the case, an exception will only be thrown when attempting to convert it to a human-readable string.

, two getter methods:
- `std::string spk::uuid::UUID::get()` - returns the binary data of the UUID (16 bytes if the UUID is valid, see above). Throws `Unset_UUID` if the UUID is empty.
- `std::string spk::uuid::UUID::to_string()` - returns a human-readable representation of the UUID (36 bytes). Throws `Unset_UUID` if the UUID is 'empty'.

and operators:
- `==` and `!=` - will treat two 'empty' UUIDs as equal.
- `bool` - UUIDs are `false` if 'empty', `true` otherwise.
