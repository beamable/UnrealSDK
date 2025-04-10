
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/EventsInDateRangeResponse.h"

#include "GetCalendarRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCalendarRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From", Category="Beam")
	FOptionalString From = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To", Category="Beam")
	FOptionalString To = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query", Category="Beam")
	FOptionalString Query = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetCalendarRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", DisplayName="Make GetCalendar",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_From,_To,_Query,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetCalendarRequest* Make(FOptionalString _From, FOptionalString _To, FOptionalString _Query, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCalendarSuccess, FBeamRequestContext, Context, UGetCalendarRequest*, Request, UEventsInDateRangeResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCalendarError, FBeamRequestContext, Context, UGetCalendarRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCalendarComplete, FBeamRequestContext, Context, UGetCalendarRequest*, Request);

using FGetCalendarFullResponse = FBeamFullResponse<UGetCalendarRequest*, UEventsInDateRangeResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCalendarFullResponse, FGetCalendarFullResponse);
