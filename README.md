# aaaEngine
Compact all-in-one AAA engine supporting most popular AAA protocols ( RADIUS / TACACS+ ) and has ambitious plans to add more protocols in future. 
`aaaEngine` can be used to model any AAA client. As of now, the engine supports single-thread, request-response based architecture, which is well suited for AAA client needs. In future, server stack will be implemented to support both client & server stacks.

## Features
* **Sleek API** - All you need is the library & include files. Only 4 APIs are needed for complete operation. It is irrespective of the underlying AAA protocol. Please refer to [how to build a client page](https://github.com/kspviswa/aaaEngine/wiki/How-to-build-the-library-using-eclipse-cdt) for more details.
* **Scalable Design** - Lot of efforts had been put into the design of `aaaEngine` to make it scalable and complete. It would take less amount of effort to introduce / depreciate a AAA protocol, without affecting the entire API design itself.
* **Ambitious plans** - `aaaEngine` project has been started recently. It was born out of frustration of not having a consolidated aaa stack for client purposes. Though started with minimum scope, the project has got ambitious plans for the future. Please refer the [enhancements](https://github.com/kspviswa/aaaEngine/labels/enhancement) lined up for this project.
* **Pure Opensource** - This project is released under [MIT license] (https://opensource.org/licenses/MIT) which makes ideal for commercial & opensource usage.

## How to build
`aaaEngine` project does not contain the `Makefile` or *pre-compiled* libraries. Instead it gives you freedom to use the source at your will under any existing build ecos-system. If you are ardent fan of `eclipse-cdt` ( like me ), then please refer to  [how to build a client page](https://github.com/kspviswa/aaaEngine/wiki/How-to-build-the-library-using-eclipse-cdt) for more details.

## Dependencies
* [ace-radius](http://sourceforge.net/projects/ace-radius/?source=typ_redirect) for RADIUS client stack
* [pam_tacplus](https://github.com/kspviswa/pam_tacplus) for TACACS+ client stack

## How to contribute
`aaaEngine` is an opensource project. Like anyother project, this project too needs community support. See the contibutors page filled with names, apart from my name, makes me immensely happy and satisfactory, giving me a sense that, I had contributed something to ever enriching opensource community, which groomed me to what I'm today. 

If you like the project's vision and wish to contribute to the project, here is the work.
* Fork your own copy of the project repo.
* Look for the [enhancements](https://github.com/kspviswa/aaaEngine/labels/enhancement) that you would be interested in and pick it up.
* Comment on the [enhancement](https://github.com/kspviswa/aaaEngine/labels/enhancement) issue and express your interest / willingness to work on the issue and get it assigned to your name. This will help me organize the work.
* Work on the enhancement, discuss with me ( a forum will be arranged if I see the project is picking up ) and finalize the changes.
* Commit the changes to your repo and raise a pull request, requesting a merge to the master of project repo. I shall review the changes and accept the merge, if deemed fit.
* If you come across any issue, prepare a test case, collect necessary logs / screenshot of the error etc and create an issue.

If you want to support the project by donating some bounty / bitcoin please contact me @ coolviswa86@gmail.com

**Note** :

The source of [ace-radius](http://sourceforge.net/projects/ace-radius/?source=typ_redirect) & some part of client source of [tacplus] (https://github.com/kspviswa/pam_tacplus) have been directly used in the project. So *aaaEngine* will literally glue both RADIUS & TACACS+ client stack together. The source of OSS have been directly used and this project has been released under [MIT license] (https://opensource.org/licenses/MIT).


Copyright © 2015 kspviswa | Released under Licensed under MIT Opensource License
