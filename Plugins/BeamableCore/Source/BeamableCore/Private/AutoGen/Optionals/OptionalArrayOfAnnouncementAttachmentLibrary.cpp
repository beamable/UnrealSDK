

#include "AutoGen/Optionals/OptionalArrayOfAnnouncementAttachmentLibrary.h"

FOptionalArrayOfAnnouncementAttachment UOptionalArrayOfAnnouncementAttachmentLibrary::MakeOptional(TArray<UAnnouncementAttachment*> Value)
{
	FOptionalArrayOfAnnouncementAttachment Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAnnouncementAttachment UOptionalArrayOfAnnouncementAttachmentLibrary::Conv_OptionalFromValue(TArray<UAnnouncementAttachment*> Value)
{
	FOptionalArrayOfAnnouncementAttachment Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfAnnouncementAttachmentLibrary::HasValue(const FOptionalArrayOfAnnouncementAttachment& Optional, TArray<UAnnouncementAttachment*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UAnnouncementAttachment*> UOptionalArrayOfAnnouncementAttachmentLibrary::GetOptionalValue(const FOptionalArrayOfAnnouncementAttachment& Optional, TArray<UAnnouncementAttachment*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

