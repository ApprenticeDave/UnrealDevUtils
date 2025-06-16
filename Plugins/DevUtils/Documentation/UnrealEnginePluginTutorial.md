# Building a custom Unreal Engine Editor Plugin.

In this tutorial we will be walking through the creation of a new Blueprint Plugin which add some new features to Unreal. This is more of a documentary of my experience trying to add functionality I felt was missing. I am going to highlight everything I have learnt.

All code is open source. If you find these plugins useful or want to support me feel free to drop me a sponsorship [page](https://github.com/sponsors/ApprenticeDave?frequency=one-time&sponsor=ApprenticeDave), the support is always appreciated.

The goal for this project was to create a number of useful plugins that would help me([AuADHD](https://embrace-autism.com/an-introduction-to-audhd/)) keep track of my progress and keep me moving forward. Otherwise I would just never finish anything.

Currently the project includes the follow plugins:

1. Markdown Node: This is a simple node which allows me to add a node in the Blueprint Graph View which we can capture Markdown documentation in which doesnt effect the game execution. As I want to share the source code I want to be able to include documentation in the nodes themselves.

Planned Plugins:

1. Todo List: This adds a panel to Unreal Editor for us to track our todos. This has its own list as well as will pull a list from the source code.
2. Graph Node auto organise and align: This will allow us to auto organise the nodes in the Blueprint Graph View. This is useful for keeping the graph tidy and easy to read.


## Concepts:

### How do Unreal Plugins Work?

### How are they structured?

### A little about SLATE


## Tutorial





# Appendix

## Other Useful Random Stuff

### Connecting Project to the GitRepo

Make sure you have created your git repo, there is an existing Unreal Engine `.gitignore` template when creating the repo which was useful as a starting point.

For this project ours is: `https://github.com/ApprenticeDave/UnrealDevUtils.git`

Open a terminal to your project directory and use the following steps:

Step 1: ` git init `

Step 2: Create a .gitignore file, you can copy the contents of the git ignore in your Github repo or look at this [one](https://github.com/github/gitignore/blob/main/UnrealEngine.gitignore).

Step 3:

git add
git commit -m "Initial commit"

git remote add origin https://github.com/ApprenticeDave/UnrealDevUtils.git

git push -u origin master






## References:
### Books:

### Documentation:


### GitHub Repos:


### Internet References:

* <a name="IR1">[IR1]</a> Quod Soler (2024), *How to create an Unreal Engine Plugin: A Step-By-Step Guide with Examples*. Available [here](https://www.quodsoler.com/blog/how-to-create-an-unreal-engine-plugin-a-step-by-step-guide-with-examples), [Last Accessed: 16/06/2025]

* <a name="IR2">[IR2]</a> Nicolas Kirsch (2015), *Create an engine plugin using Blank Plugin*. Available [here](https://puppet-master.net/blog/docs/unreal-engine-4/programming/create-an-engine-plugin-using-blank-plugin/), [Last Accessed: 16/06/2025]