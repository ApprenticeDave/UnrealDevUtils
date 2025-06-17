#include "Modules/ModuleManager.h"

/*
* Base interface for the Blueprint Markdown module. This module provides functionality for
* getting the module instance and checking if the module is available.
*/
class IBlueprintMarkdownModule : public IModuleInterface {
public:
	/**
	 * Allows other parts of the code to access the Blueprint Markdown module through the
	 * Unreal Engine's module manager system.
	 *
	 * @return A reference to the Blueprint Markdown module.
	 */
	static inline IBlueprintMarkdownModule &Get() {return FModuleManager::LoadModuleChecked<IBlueprintMarkdownModule>("BlueprintMarkdown");}

	/**
	 * Checks if the Blueprint Markdown module is currently loaded.
	 * 
	 * @return true if the module is loaded, false otherwise.
	 */
	static inline bool IsAvailable() {return FModuleManager::Get().IsModuleLoaded("BlueprintMarkdown");}
};


