
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAnnouncementAttachment.h"

FOptionalArrayOfAnnouncementAttachment::FOptionalArrayOfAnnouncementAttachment()
{
	Val = TArray<UAnnouncementAttachment*>();
	IsSet = false;
}

FOptionalArrayOfAnnouncementAttachment::FOptionalArrayOfAnnouncementAttachment(TArray<UAnnouncementAttachment*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfAnnouncementAttachment::GetAddr() const { return &Val; }

void FOptionalArrayOfAnnouncementAttachment::Set(const void* Data)
{
	Val = *((TArray<UAnnouncementAttachment*>*)Data);
	IsSet = true;
}