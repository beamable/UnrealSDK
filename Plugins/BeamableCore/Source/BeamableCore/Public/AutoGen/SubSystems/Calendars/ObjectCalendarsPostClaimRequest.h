
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/CalendarClaimRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "ObjectCalendarsPostClaimRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectCalendarsPostClaimRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCalendarClaimRequestBody* Body = {};

	// Beam Base Request Declaration
	UObjectCalendarsPostClaimRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Calendars", DisplayName="Beam - Make ObjectCalendarsPostClaim",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectCalendarsPostClaimRequest* Make(int64 _ObjectId, FString _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectCalendarsPostClaimSuccess, FBeamRequestContext, Context, UObjectCalendarsPostClaimRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectCalendarsPostClaimError, FBeamRequestContext, Context, UObjectCalendarsPostClaimRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectCalendarsPostClaimComplete, FBeamRequestContext, Context, UObjectCalendarsPostClaimRequest*, Request);

using FObjectCalendarsPostClaimFullResponse = FBeamFullResponse<UObjectCalendarsPostClaimRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectCalendarsPostClaimFullResponse, FObjectCalendarsPostClaimFullResponse);
