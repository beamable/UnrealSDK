
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AnnouncementDto.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostAnnouncementsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostAnnouncementsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAnnouncementDto* Body = {};

	// Beam Base Request Declaration
	UPostAnnouncementsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make PostAnnouncements",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_StartDate,_Gift,_EndDate,_Tags,_StatRequirements,_Attachments,_ClientData,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostAnnouncementsRequest* Make(ULocalizationRef* _Body, FString _Channel, FString _Symbol, ULocalizationRef* _Title, ULocalizationRef* _Summary, FOptionalString _StartDate, FOptionalPlayerReward _Gift, FOptionalString _EndDate, FOptionalArrayOfString _Tags, FOptionalArrayOfPlayerStatRequirement _StatRequirements, FOptionalArrayOfAnnouncementAttachment _Attachments, FOptionalMapOfString _ClientData, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAnnouncementsSuccess, FBeamRequestContext, Context, UPostAnnouncementsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAnnouncementsError, FBeamRequestContext, Context, UPostAnnouncementsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostAnnouncementsComplete, FBeamRequestContext, Context, UPostAnnouncementsRequest*, Request);

using FPostAnnouncementsFullResponse = FBeamFullResponse<UPostAnnouncementsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostAnnouncementsFullResponse, FPostAnnouncementsFullResponse);
