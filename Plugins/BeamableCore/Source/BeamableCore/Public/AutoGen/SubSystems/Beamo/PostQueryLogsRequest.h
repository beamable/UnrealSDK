
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetLogsInsightUrlRequestBody.h"
#include "BeamableCore/Public/AutoGen/Query.h"

#include "PostQueryLogsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostQueryLogsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGetLogsInsightUrlRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostQueryLogsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostQueryLogs",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_StartTime,_Filter,_EndTime,_Order,_Limit,_Filters,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostQueryLogsRequest* Make(FString _ServiceName, FOptionalInt64 _StartTime, FOptionalString _Filter, FOptionalInt64 _EndTime, FOptionalString _Order, FOptionalInt32 _Limit, FOptionalArrayOfString _Filters, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostQueryLogsSuccess, FBeamRequestContext, Context, UPostQueryLogsRequest*, Request, UQuery*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostQueryLogsError, FBeamRequestContext, Context, UPostQueryLogsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostQueryLogsComplete, FBeamRequestContext, Context, UPostQueryLogsRequest*, Request);

using FPostQueryLogsFullResponse = FBeamFullResponse<UPostQueryLogsRequest*, UQuery*>;
DECLARE_DELEGATE_OneParam(FOnPostQueryLogsFullResponse, FPostQueryLogsFullResponse);
