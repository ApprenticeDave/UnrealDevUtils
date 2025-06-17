#include "CoreMinimal.h"
#include "K2Node.h"
#include "UK2Node_BlueprintMarkdownNode.generated.h"

UCLASS()
class BLUEPRINTMARKDOWN_API UK2Node_BlueprintMarkdownNode : public UK2Node
{
	GENERATED_BODY()

public:
	/** 
	 * Override the function to get the menu actions for this node.
	 * This will allow the node to be added to the Blueprint editor's
	 * context menu.
	 */
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	// virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	// virtual FText GetMenuCategory() const override;
	// virtual FText GetTooltipText() const override;
	// virtual FText GetToolTipHeading() const override;
	// virtual FText GetKeywords() const override;
	// virtual bool ShouldDrawCompact() const override;
	// virtual FText GetCompactNodeTitle() const override;
	//
	// virtual bool IsNodePure() const override { return true; }
};