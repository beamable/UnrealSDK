

#include "OptionalArrayOfAnnouncementAttachmentLibrary.h"

FOptionalArrayOfAnnouncementAttachment UOptionalArrayOfAnnouncementAttachmentLibrary::MakeOptionalArrayOfAnnouncementAttachment(TArray<UAnnouncementAttachment*> Value)
{
	FOptionalArrayOfAnnouncementAttachment Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAnnouncementAttachment UOptionalArrayOfAnnouncementAttachmentLibrary::Conv_OptionalArrayOfAnnouncementAttachmentFromValue(TArray<UAnnouncementAttachment*> Value)
{
	FOptionalArrayOfAnnouncementAttachment Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

