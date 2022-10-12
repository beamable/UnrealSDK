
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/BatchReadStatsResponse.h"

#include "GetClientBatchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetClientBatchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Ids")
	FString ObjectIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats")
	FOptionalString Stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Format")
	FOptionalString Format;

	// Body Params
	

	// Beam Base Request Declaration
	UGetClientBatchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Stats,_Format,Outer"))
	static UGetClientBatchRequest* MakeGetClientBatchRequest(FString _ObjectIds, FOptionalString _Stats, FOptionalString _Format, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientBatchSuccess, FBeamRequestContext, Context, UGetClientBatchRequest*, Request, UBatchReadStatsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientBatchError, FBeamRequestContext, Context, UGetClientBatchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetClientBatchComplete, FBeamRequestContext, Context, UGetClientBatchRequest*, Request);

using FGetClientBatchFullResponse = FBeamFullResponse<UGetClientBatchRequest*, UBatchReadStatsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetClientBatchFullResponse, FGetClientBatchFullResponse);
