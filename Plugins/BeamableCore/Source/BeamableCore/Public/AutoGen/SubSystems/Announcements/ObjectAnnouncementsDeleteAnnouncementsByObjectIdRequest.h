
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AnnouncementRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "ObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAnnouncementRequestBody* Body = {};

	// Beam Base Request Declaration
	UObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make ObjectAnnouncementsDeleteAnnouncementsByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Announcement,_Announcements,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest* Make(int64 _ObjectId, FOptionalString _Announcement, FOptionalArrayOfString _Announcements, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsDeleteAnnouncementsByObjectIdSuccess, FBeamRequestContext, Context, UObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsDeleteAnnouncementsByObjectIdError, FBeamRequestContext, Context, UObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectAnnouncementsDeleteAnnouncementsByObjectIdComplete, FBeamRequestContext, Context, UObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest*, Request);

using FObjectAnnouncementsDeleteAnnouncementsByObjectIdFullResponse = FBeamFullResponse<UObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectAnnouncementsDeleteAnnouncementsByObjectIdFullResponse, FObjectAnnouncementsDeleteAnnouncementsByObjectIdFullResponse);
