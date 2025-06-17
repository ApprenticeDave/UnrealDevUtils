#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IBlueprintMarkdownModule.h"


/**
 * BlueprintMarkdown Module to handle the integration of Markdown Node support in Blueprints.
 */
class FBlueprintMarkdownModule : public IBlueprintMarkdownModule
{
private:
    
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
