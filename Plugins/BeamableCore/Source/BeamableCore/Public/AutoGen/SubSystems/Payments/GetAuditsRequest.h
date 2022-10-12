
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/ListAuditResponse.h"

#include "GetAuditsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAuditsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Providerid")
	FOptionalString Providerid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider")
	FOptionalString Provider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State")
	FOptionalString State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Txid")
	FOptionalInt64 Txid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player")
	FOptionalInt64 Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start")
	FOptionalInt32 Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;

	// Body Params
	

	// Beam Base Request Declaration
	UGetAuditsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Providerid,_Provider,_State,_Txid,_Player,_Start,_Limit,Outer"))
	static UGetAuditsRequest* MakeGetAuditsRequest(FOptionalString _Providerid, FOptionalString _Provider, FOptionalString _State, FOptionalInt64 _Txid, FOptionalInt64 _Player, FOptionalInt32 _Start, FOptionalInt32 _Limit, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAuditsSuccess, FBeamRequestContext, Context, UGetAuditsRequest*, Request, UListAuditResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAuditsError, FBeamRequestContext, Context, UGetAuditsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAuditsComplete, FBeamRequestContext, Context, UGetAuditsRequest*, Request);

using FGetAuditsFullResponse = FBeamFullResponse<UGetAuditsRequest*, UListAuditResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAuditsFullResponse, FGetAuditsFullResponse);
