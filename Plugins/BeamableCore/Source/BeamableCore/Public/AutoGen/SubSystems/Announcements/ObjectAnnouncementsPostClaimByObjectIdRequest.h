
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AnnouncementRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "ObjectAnnouncementsPostClaimByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectAnnouncementsPostClaimByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
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
	UObjectAnnouncementsPostClaimByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make ObjectAnnouncementsPostClaimByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Announcement,_Announcements,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectAnnouncementsPostClaimByObjectIdRequest* Make(int64 _ObjectId, FOptionalString _Announcement, FOptionalArrayOfString _Announcements, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsPostClaimByObjectIdSuccess, FBeamRequestContext, Context, UObjectAnnouncementsPostClaimByObjectIdRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsPostClaimByObjectIdError, FBeamRequestContext, Context, UObjectAnnouncementsPostClaimByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectAnnouncementsPostClaimByObjectIdComplete, FBeamRequestContext, Context, UObjectAnnouncementsPostClaimByObjectIdRequest*, Request);

using FObjectAnnouncementsPostClaimByObjectIdFullResponse = FBeamFullResponse<UObjectAnnouncementsPostClaimByObjectIdRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectAnnouncementsPostClaimByObjectIdFullResponse, FObjectAnnouncementsPostClaimByObjectIdFullResponse);
