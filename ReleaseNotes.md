Sequential Button Arduino Library
2017-2018 SMFSW

Feel free to share your thoughts @ xgarmanboziax@gmail.com about:
	- issues encountered
	- optimizations
	- improvements & new functionalities

------------

** Actual:
v1.5	15 July 2018:
- Passing whole instance in callbacks instead of just pin - addressing [github issue #1](https://github.com/SMFSW/SeqButton/issues/1)

v1.4.1	15 July 2018:
- Added TimingExample sketch

v1.4	14 July 2018:
- Adding passing pin number in callbacks (and updated examples) - addressing [github issue #1](https://github.com/SMFSW/SeqButton/issues/1)
- Adding support for unit tests and doxygen documentation generation with Travis CI
- Updated README.md

v1.3.1	20 Jan 2018:
- Added 2 more complex examples (combination & sequence detection)

v1.3	21 Nov 2017:
- Time variables now on 32b
- Added const qualifier for function parameters

v1.2	12 Jul 2017:
- compliance with Arduino v1.5+ IDE source located in src subfolder

v1.1	29 June 2017:
- Added unsigned cast for time test (may have caused issues on 32b boards)

v1.0	21 March 2017:
- First release
