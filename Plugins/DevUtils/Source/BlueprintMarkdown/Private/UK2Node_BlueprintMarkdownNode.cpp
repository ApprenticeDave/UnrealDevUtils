#include "UK2Node_BlueprintMarkdownNode.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "Slate/SMarkdownEditorWidget.h"

#define LOCTEXT_NAMESPACE "DevUtils"

void UK2Node_BlueprintMarkdownNode::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2Node_BlueprintMarkdownNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("BlueprintMarkdownNode_Title", "Documentation");
}

FText UK2Node_BlueprintMarkdownNode::GetMenuCategory() const
{
	return Super::GetMenuCategory();
}

FText UK2Node_BlueprintMarkdownNode::GetTooltipText() const
{
	return Super::GetTooltipText();
}

FText UK2Node_BlueprintMarkdownNode::GetToolTipHeading() const
{
	return Super::GetToolTipHeading();
}

FText UK2Node_BlueprintMarkdownNode::GetKeywords() const
{
	return Super::GetKeywords();
}

TSharedPtr<SGraphNode> UK2Node_BlueprintMarkdownNode::CreateVisualWidget()
{
	return SNew(SMarkdownEditorWidget, this);
}

void UK2Node_BlueprintMarkdownNode::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
}


#undef LOCTEXT_NAMESPACE
