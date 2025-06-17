# Building a custom Unreal Engine Editor Plugin.

In this tutorial we will be walking through the creation of a new Blueprint Plugin which add some new features to Unreal. This is more of a documentary of my experience trying to add functionality I felt was missing. I am going to highlight everything I have learnt.

All code is open source. If you find these plugins useful or want to support me feel free to drop me a sponsorship [page](https://github.com/sponsors/ApprenticeDave?frequency=one-time&sponsor=ApprenticeDave), the support is always appreciated.

The goal for this project was to create a number of useful plugins that would help me([AuADHD](https://embrace-autism.com/an-introduction-to-audhd/)) keep track of my progress and keep me moving forward. Otherwise I would just never finish anything.

The project includes the follow plugins:

1. Markdown Node: This is a simple node which allows me to add a node in the Blueprint Graph View which we can capture Markdown documentation in which doesnt effect the game execution. As I want to share the source code I want to be able to include documentation in the nodes themselves.

Planned Plugins:

1. Todo List: This adds a panel to Unreal Editor for us to track our todos. This has its own list as well as will pull a list from the source code.
2. Graph Node auto organise and align: This will allow us to auto organise the nodes in the Blueprint Graph View. This is useful for keeping the graph tidy and easy to read.

## Tutorial

We will need to understand a little about how Unreal's plugin system works. There are two types of plugins, Engine Plugins and Project Plugins. Engine plugins are installed in the engine directory and can be used by any project that uses that engine version. Project plugins are installed in the project directory and can only be used by that project. The type is determined by where the plugin is installed.

Unreal Engine has a number of templates for creating plugins, we will be using the "Blank Plugin" template. This template is a good starting point for creating a new plugin as it provides a basic structure and some example code.

### Creating the Plugin 
The Easiest way to create a new plugin is to use the Unreal Engine Editor. To do this, follow these steps:

1. Either open an existing project or create a new one.
2. In the main menu, go to `Edit` -> `Plugins`.

![01. Navigate Plugins Menu.png](../Assets/screenshots/01.%20Navigate%20Plugins%20Menu.png)

3. In the Plugins window, click on the `New Plugin` button.

![02. Add Plugin Button.png](../Assets/screenshots/02.%20Add%20Plugin%20Button.png)

4. In the Create a New Plugin window, select the `Blank Plugin` template.

![03. New Plugin Details Screen.png](../Assets/screenshots/03.%20New%20Plugin%20Details%20Screen.png)

5. Give your plugin a name, for example `DevUtils`.
6. Click on the `Create Plugin` button.

This will create a new plugin in the `Plugins` directory of your project.

#### Structure of a Plugin Directory

When you create a new plugin in Unreal Engine, it will create a directory structure for you. The structure is as follows:

A plugin is a directory that contains a number of files and directories. The main files are:
- `*.uplugin`: This is the plugin descriptor file, it contains metadata about the plugin such as its name, version, modules, and dependencies.
- `Source/`: This directory contains the source code for the plugin, it is structured like a normal Unreal Engine project with a module which contains a `Public/` and `Private/` directory.
- `Resources/`: This directory contains any resources that the plugin needs, such as images or icons.
- `Content/`: This directory contains any content that the plugin needs, such as Blueprints or materials.
- `Documentation/`: This directory contains any documentation for the plugin, such as this tutorial.
- `Binaries/`: This directory contains the compiled binaries for the plugin, it is generated when the plugin is built.
- `Config/`: This directory contains any configuration files for the plugin, such as the `DefaultEngine.ini` file.
- `Intermediate/`: This directory contains any intermediate files that are generated when the plugin is built, such as the `Build.cs` file.

#### Important Files

- `*.uplugin`: This is the plugin descriptor file, it contains metadata about the plugin such as its name, version, modules, and dependencies. It is used by Unreal Engine to load the plugin and its modules.
- `*.Build.cs`: This is the build script for the plugin, it contains the build settings for the plugin such as the modules that are included, the dependencies, and the include paths. It is used by Unreal Engine to compile the plugin.
- `*.h` and `*.cpp`: These are the header and source files for the plugin, they contain the code for the plugin. The header files contain the declarations of the classes and functions, while the source files contain the definitions of the classes and functions.
- `*.ini`: These are the configuration files for the plugin, they contain any configuration settings for the plugin. The `DefaultEngine.ini` file is used to configure the plugin's settings in the Unreal Engine Editor.


#### Modules
A plugin can contain one or more modules, each module is a self-contained unit of code that can be compiled and loaded independently. Each module has its own `*.Build.cs` file which contains the build settings for the module. The module can be either a "Runtime" module or an "Editor" module. A runtime module is used in the game, while an editor module is used in the editor.

Modules are useful for organizing code and separating functionality. For example, you could have a module for the game logic, a module for the UI, and a module for the editor tools. This allows you to keep your code organized and makes it easier to maintain.

# Appendix

## Other Useful Random Stuff

### Connecting Project to the GitRepo

Make sure you have created your git repo, there is an existing Unreal Engine `.gitignore` template when creating the repo which was useful as a starting point.

For this project ours is: `https://github.com/ApprenticeDave/UnrealDevUtils.git`

Open a terminal to your project directory and use the following steps:

Step 1: ` git init `

Step 2: Create a .gitignore file, you can copy the contents of the git ignore in your Github repo or look at this [one](https://github.com/github/gitignore/blob/main/UnrealEngine.gitignore).

Step 3:

```
// Add changes
git add

// Commit changes
git commit -m "Initial commit"

// Add Remote Repo
git remote add origin https://github.com/ApprenticeDave/UnrealDevUtils.git

// Push changes
git push -u origin master
```





## References:
### Books:

### Documentation:
https://unrealist.org/custom-blueprint-nodes/
https://docs.unrealengine.com/5.3/en-US/ProgrammingAndScripting/Plugins/CreatingPlugins/
https://unrealist.org/custom-blueprint-nodes/
https://medium.com/@lemapp09/learning-unreal-creating-custom-blueprint-nodes-in-c-3ddb54eaf254


### GitHub Repos:
* https://medium.com/@lemapp09/learning-unreal-creating-custom-blueprint-nodes-in-c-3ddb54eaf254
* https://github.com/BrUnOXaVIeRLeiTE/Unreal-Magic-Nodes
* https://github.com/Drakynfly/HeartGraph

### Internet References:

* https://olssondev.github.io/2023-02-13-K2Nodes/

* <a name="IR1">[IR1]</a> Quod Soler (2024), *How to create an Unreal Engine Plugin: A Step-By-Step Guide with Examples*. Available [here](https://www.quodsoler.com/blog/how-to-create-an-unreal-engine-plugin-a-step-by-step-guide-with-examples), [Last Accessed: 16/06/2025]

* <a name="IR2">[IR2]</a> Nicolas Kirsch (2015), *Create an engine plugin using Blank Plugin*. Available [here](https://puppet-master.net/blog/docs/unreal-engine-4/programming/create-an-engine-plugin-using-blank-plugin/), [Last Accessed: 16/06/2025]