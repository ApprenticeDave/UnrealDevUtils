#pragma once

#include "CoreMinimal.h"
#include "UK2Node_BlueprintMarkdownNode.h"
#include "KismetNodes/SGraphNodeK2Base.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Layout/SScaleBox.h"
#include "cmark.h"


class SMarkdownEditorWidget  : public SGraphNodeK2Base
{
public:
	SLATE_BEGIN_ARGS(SMarkdownEditorWidget)
	{
	}

	SLATE_END_ARGS()

private:
	TSharedPtr<SCheckBox> EditModeCheckBox;
	TSharedPtr<SRichTextBlock> MarkdownPreviewTextBlock;
	TSharedPtr<SBox> MarkdownPreviewBox;
	TSharedPtr<SBox> MarkdownEditorBox;
	TSharedPtr<SMultiLineEditableTextBox> MarkdownEditorTextBox;
	TSharedPtr<SBox> NodeContainer;
	
	void OnEditModeChanged(ECheckBoxState CheckBoxState) const;
	bool bIsEditModeEnabled = true;
	bool bIsHorizontalResize = false;
	bool bIsVerticalResize = false;
	bool bIsResizingMarkdownNode = false;
	float ResizeAreaSize = 5.0f;
	FVector2f OriginalNodeSize = FVector2f::ZeroVector;
	FVector2f NodeLocalResizeStartPosition = FVector2f::ZeroVector;
	void UpdateResizeState(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
public:
	void OnMarkdownTextChanged(const FText& Text) const;
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, UK2Node* InNode);
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
};
