
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/AnnouncementRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "ObjectAnnouncementsPostClaimRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectAnnouncementsPostClaimRequest : public UObject, public IBeamBaseRequestInterface
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
	UObjectAnnouncementsPostClaimRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Announcements", DisplayName="Beam - Make ObjectAnnouncementsPostClaim",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Announcement,_Announcements,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectAnnouncementsPostClaimRequest* Make(int64 _ObjectId, FOptionalString _Announcement, FOptionalArrayOfString _Announcements, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsPostClaimSuccess, FBeamRequestContext, Context, UObjectAnnouncementsPostClaimRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsPostClaimError, FBeamRequestContext, Context, UObjectAnnouncementsPostClaimRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectAnnouncementsPostClaimComplete, FBeamRequestContext, Context, UObjectAnnouncementsPostClaimRequest*, Request);

using FObjectAnnouncementsPostClaimFullResponse = FBeamFullResponse<UObjectAnnouncementsPostClaimRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectAnnouncementsPostClaimFullResponse, FObjectAnnouncementsPostClaimFullResponse);
