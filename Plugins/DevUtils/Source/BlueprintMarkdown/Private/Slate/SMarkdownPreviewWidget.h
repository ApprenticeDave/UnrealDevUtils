#pragma once
#include "CoreMinimal.h"
#include "KismetNodes/SGraphNodeK2Base.h"

class SMarkdownPreviewWidget : public SGraphNodeK2Base
{
public:
	SLATE_BEGIN_ARGS(SMarkdownPreviewWidget)
	{
	}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, UK2Node* InNode);
};
