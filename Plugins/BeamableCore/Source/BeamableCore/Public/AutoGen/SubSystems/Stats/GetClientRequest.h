
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/StatsResponse.h"

#include "GetClientRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetClientRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats")
	FOptionalString Stats;

	// Body Params
	

	// Beam Base Request Declaration
	UGetClientRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Stats,Outer"))
	static UGetClientRequest* MakeGetClientRequest(FString _ObjectId, FOptionalString _Stats, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientSuccess, FBeamRequestContext, Context, UGetClientRequest*, Request, UStatsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientError, FBeamRequestContext, Context, UGetClientRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetClientComplete, FBeamRequestContext, Context, UGetClientRequest*, Request);

using FGetClientFullResponse = FBeamFullResponse<UGetClientRequest*, UStatsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetClientFullResponse, FGetClientFullResponse);
