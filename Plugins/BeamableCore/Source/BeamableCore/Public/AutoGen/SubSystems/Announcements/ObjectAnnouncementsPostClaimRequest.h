
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AnnouncementRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "ObjectAnnouncementsPostClaimRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectAnnouncementsPostClaimRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UAnnouncementRequestBody* Body;

	// Beam Base Request Declaration
	UObjectAnnouncementsPostClaimRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Announcement,_Announcements,Outer"))
	static UObjectAnnouncementsPostClaimRequest* MakeObjectAnnouncementsPostClaimRequest(int64 _ObjectId, FOptionalString _Announcement, FOptionalArrayOfString _Announcements, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsPostClaimSuccess, FBeamRequestContext, Context, UObjectAnnouncementsPostClaimRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsPostClaimError, FBeamRequestContext, Context, UObjectAnnouncementsPostClaimRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectAnnouncementsPostClaimComplete, FBeamRequestContext, Context, UObjectAnnouncementsPostClaimRequest*, Request);

using FObjectAnnouncementsPostClaimFullResponse = FBeamFullResponse<UObjectAnnouncementsPostClaimRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectAnnouncementsPostClaimFullResponse, FObjectAnnouncementsPostClaimFullResponse);
