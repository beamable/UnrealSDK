
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/ListAuditResponse.h"

#include "GetAuditsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAuditsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Providerid", Category="Beam")
	FOptionalString Providerid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider", Category="Beam")
	FOptionalString Provider = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State", Category="Beam")
	FOptionalString State = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Txid", Category="Beam")
	FOptionalInt64 Txid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player", Category="Beam")
	FOptionalInt64 Player = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start", Category="Beam")
	FOptionalInt32 Start = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetAuditsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetAudits",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Providerid,_Provider,_State,_Txid,_Player,_Start,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAuditsRequest* Make(FOptionalString _Providerid, FOptionalString _Provider, FOptionalString _State, FOptionalInt64 _Txid, FOptionalInt64 _Player, FOptionalInt32 _Start, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAuditsSuccess, FBeamRequestContext, Context, UGetAuditsRequest*, Request, UListAuditResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAuditsError, FBeamRequestContext, Context, UGetAuditsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAuditsComplete, FBeamRequestContext, Context, UGetAuditsRequest*, Request);

using FGetAuditsFullResponse = FBeamFullResponse<UGetAuditsRequest*, UListAuditResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAuditsFullResponse, FGetAuditsFullResponse);
