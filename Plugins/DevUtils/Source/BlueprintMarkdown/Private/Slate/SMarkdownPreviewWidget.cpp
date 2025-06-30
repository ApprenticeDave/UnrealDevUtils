#include "SMarkdownPreviewWidget.h"

void SMarkdownPreviewWidget::Construct(const FArguments& InArgs, UK2Node* InNode)
{
	GraphNode = InNode;

	UpdateGraphNode();
}
