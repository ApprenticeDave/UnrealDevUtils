#include "SMarkdownEditorWidget.h"

void SMarkdownEditorWidget::Construct(const FArguments& InArgs, UK2Node* InNode)
{
	GraphNode = InNode;

	// Reference to the Node so we can access items to the blueprint. 
	auto* BlueprintNode = Cast<UK2Node_BlueprintMarkdownNode>(GraphNode);
	bIsResizingMarkdownNode = false;
	
	// Initialise the core components so we can access them easer
	
	MarkdownEditorTextBox = SNew(SMultiLineEditableTextBox)
								.AllowMultiLine(true)
								.AutoWrapText(true)
								.VScrollBar(SNew(SScrollBar))
								.OnTextChanged(this, &SMarkdownEditorWidget::OnMarkdownTextChanged)
								;
	MarkdownEditorTextBox->SetText(BlueprintNode->MarkdownText);
	MarkdownPreviewTextBlock = SNew(SRichTextBlock)
		.Text(BlueprintNode->MarkdownText)
		.AutoWrapText(true)
		.Justification(ETextJustify::Left)
		.TextStyle(FAppStyle::Get(), "NormalText");;
	EditModeCheckBox = SNew(SCheckBox)
		.IsChecked(bIsEditModeEnabled ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
		.OnCheckStateChanged(this, &SMarkdownEditorWidget::OnEditModeChanged);
	MarkdownEditorBox = SNew(SBox)
	[
		MarkdownEditorTextBox.ToSharedRef()
	];
	
	MarkdownPreviewBox = SNew(SBox)
    [
        MarkdownPreviewTextBlock.ToSharedRef()
    ];

	NodeContainer = SNew(SBox)
		.Padding(FMargin(5))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
						[
							MarkdownEditorTextBox.ToSharedRef()
						]
					+ SHorizontalBox::Slot()
						[
							MarkdownPreviewBox.ToSharedRef()
						]
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Left)
						.Padding(FMargin(5))
						[
							SNew(STextBlock)
								.Text(FText::FromString("Edit"))
						]
					+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Left)
						.Padding(FMargin(5))
						[
							EditModeCheckBox.ToSharedRef()
							
						]
				]
		];

	
	UpdateGraphNode();
}

void SMarkdownEditorWidget::OnEditModeChanged(ECheckBoxState CheckBoxState) const
{
	auto* BlueprintNode = Cast<UK2Node_BlueprintMarkdownNode>(GraphNode);
	if (!BlueprintNode)
	{
		return;
	}
	
	switch (CheckBoxState)
	{
	case ECheckBoxState::Checked:
		// Handle checked state
		MarkdownEditorTextBox->SetVisibility(EVisibility::Visible);
		break;
	case ECheckBoxState::Unchecked:
		// Handle unchecked state
		MarkdownEditorTextBox->SetVisibility(EVisibility::Collapsed);
		break;
	case ECheckBoxState::Undetermined:
		// This is not a supported state for a checkbox, but we handle it just in case
		UE_LOG(LogTemp, Warning, TEXT("The check box state is an unexpected value!"));
		break;
	}

}

void SMarkdownEditorWidget::UpdateResizeState(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!bIsResizingMarkdownNode)
	{
		FVector2D LocalMousePosition = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
		FVector2D LocalSize = MyGeometry.GetLocalSize();
		bIsHorizontalResize = false;
		bIsVerticalResize = false;
		bIsHorizontalResize = (LocalMousePosition.X <= ResizeAreaSize || LocalMousePosition.X >= (LocalSize.X - ResizeAreaSize));
		bIsVerticalResize = (LocalMousePosition.Y <= ResizeAreaSize || LocalMousePosition.Y >= (LocalSize.Y - ResizeAreaSize));
		if (bIsHorizontalResize || bIsVerticalResize)
		{
			UE_LOG(LogTemp, Log, TEXT("RESIZE AREA DETECTED: %s"), *LocalMousePosition.ToString());
		}
	}
}

	
void SMarkdownEditorWidget::OnMarkdownTextChanged(const FText& Text) const
{
	auto* BlueprintNode = Cast<UK2Node_BlueprintMarkdownNode>(GraphNode);

	BlueprintNode->MarkdownText = Text;
	
	FText richtext = FText::FromString(BlueprintNode->MarkdownText.ToString());
	MarkdownPreviewTextBlock->SetText(richtext);
}

TSharedRef<SWidget> SMarkdownEditorWidget::CreateNodeContentArea()
{
	//auto* BlueprintNode = Cast<UK2Node_BlueprintMarkdownNode>(GraphNode);
	return NodeContainer.ToSharedRef();
}
/*
 * Show the appropriate cursor based on the cursor position on the node. 
 * - `ResizeSouthEast` - Diagonal resize (↘)
 * - `ResizeSouthWest` - Diagonal resize (↙)
 * - `ResizeLeftRight` - Horizontal resize (↔)
 * - `ResizeUpDown` - Vertical resize (↕)
 */
FCursorReply SMarkdownEditorWidget::OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const
{

	if (bIsHorizontalResize || bIsVerticalResize)
	{
		if (bIsHorizontalResize && bIsVerticalResize)
		{
			FVector2D LocalMousePosition = MyGeometry.AbsoluteToLocal(CursorEvent.GetScreenSpacePosition());
			FVector2D LocalSize = MyGeometry.GetLocalSize();
			
			if (
					(
						(LocalMousePosition.X <= ResizeAreaSize)
						&&
						(LocalMousePosition.Y <= ResizeAreaSize)
					)
					||
					(
						(LocalMousePosition.X >= (LocalSize.X - ResizeAreaSize))
						&&
						(LocalMousePosition.Y >= (LocalSize.Y - ResizeAreaSize))
					)
				)
			{
				return FCursorReply::Cursor(EMouseCursor::ResizeSouthEast);
			}
			else if (
						(
							(LocalMousePosition.X <= ResizeAreaSize)
							&&
							(LocalMousePosition.Y >= (LocalSize.Y - ResizeAreaSize))
						)
						||
						(
							(LocalMousePosition.X >= (LocalSize.X - ResizeAreaSize))
							&&
							(LocalMousePosition.Y <= ResizeAreaSize)
						)
					)
			{
				return FCursorReply::Cursor(EMouseCursor::ResizeSouthWest);
			}
		}
		else if (bIsHorizontalResize)
		{
			return FCursorReply::Cursor(EMouseCursor::ResizeLeftRight);
		}
		else if (bIsVerticalResize)
		{
			return FCursorReply::Cursor(EMouseCursor::ResizeUpDown);
		}
	}
	return FCursorReply::Unhandled();
}

FReply SMarkdownEditorWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	UpdateResizeState(MyGeometry, MouseEvent);
	
	if (bIsResizingMarkdownNode)
	{
		const FVector2f ScreenMousePosition = MouseEvent.GetScreenSpacePosition();
		
		const FVector2f LocalMouseDelta = MyGeometry.AbsoluteToLocal(
			ScreenMousePosition
		) - NodeLocalResizeStartPosition;

		FVector2f NewSize = OriginalNodeSize + LocalMouseDelta;
		if (bIsHorizontalResize)
		{
			NewSize.X = FMath::Clamp(NewSize.X, 600.0f, 2000.0f);
			NodeContainer->SetWidthOverride(NewSize.X);
		}
		
		if (bIsVerticalResize)
		{
			NewSize.Y = FMath::Clamp(NewSize.Y, 300.0f, 1500.0f);
			NodeContainer->SetWidthOverride(NewSize.X);
		}
		
		UE_LOG(LogTemp, Log, TEXT("RESIZE TO: %s"), *NewSize.ToString());
	
		
		NodeContainer->SetHeightOverride(NewSize.Y);
		
		return FReply::Handled();
	}
	
    return SGraphNode::OnMouseMove(MyGeometry, MouseEvent);
}

FReply SMarkdownEditorWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (bIsHorizontalResize || bIsVerticalResize)
	{
		UE_LOG(LogTemp, Log, TEXT("BEGIN RESIZE"));
		bIsResizingMarkdownNode = true;
		OriginalNodeSize = MyGeometry.GetLocalSize();
		NodeLocalResizeStartPosition = MyGeometry.AbsoluteToLocal(
MouseEvent.GetScreenSpacePosition());
		return FReply::Handled();
	}
	
	return SGraphNodeK2Base::OnMouseButtonDown(MyGeometry, MouseEvent);
}

FReply SMarkdownEditorWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	UE_LOG(LogTemp, Log, TEXT("END RESIZE"));
	bIsResizingMarkdownNode = false;
	bIsHorizontalResize = false;
	bIsVerticalResize = false;
	
	return SGraphNodeK2Base::OnMouseButtonUp(MyGeometry, MouseEvent);
}

