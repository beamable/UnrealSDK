
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/AnnouncementDto.h"
#include "AutoGen/EmptyResponse.h"

#include "PostAnnouncementsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostAnnouncementsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UAnnouncementDto* Body;

	// Beam Base Request Declaration
	UPostAnnouncementsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_StartDate,_Tags,_Gift,_StatRequirements,_ClientData,_EndDate,_Attachments,Outer"))
	static UPostAnnouncementsRequest* MakePostAnnouncementsRequest(ULocalizationRef* _Body, FString _Channel, FOptionalString _StartDate, FOptionalArrayOfString _Tags, FOptionalPlayerReward _Gift, FOptionalArrayOfPlayerStatRequirement _StatRequirements, FString _Symbol, FOptionalMapOfString _ClientData, FOptionalString _EndDate, ULocalizationRef* _Title, FOptionalArrayOfAnnouncementAttachment _Attachments, ULocalizationRef* _Summary, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAnnouncementsSuccess, FBeamRequestContext, Context, UPostAnnouncementsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAnnouncementsError, FBeamRequestContext, Context, UPostAnnouncementsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostAnnouncementsComplete, FBeamRequestContext, Context, UPostAnnouncementsRequest*, Request);

using FPostAnnouncementsFullResponse = FBeamFullResponse<UPostAnnouncementsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostAnnouncementsFullResponse, FPostAnnouncementsFullResponse);
