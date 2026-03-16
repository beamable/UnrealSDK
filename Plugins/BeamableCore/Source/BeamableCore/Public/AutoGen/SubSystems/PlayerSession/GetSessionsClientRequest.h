
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/SessionClientHistoryResponse.h"

#include "GetSessionsClientRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSessionsClientRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Month", Category="Beam")
	FOptionalInt32 Month = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Year", Category="Beam")
	FOptionalInt32 Year = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetSessionsClientRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|PlayerSession|Utils|Make/Break", DisplayName="Make GetSessionsClient",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Month,_Year,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetSessionsClientRequest* Make(FString _PlayerId, FOptionalInt32 _Month, FOptionalInt32 _Year, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSessionsClientSuccess, FBeamRequestContext, Context, UGetSessionsClientRequest*, Request, USessionClientHistoryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSessionsClientError, FBeamRequestContext, Context, UGetSessionsClientRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSessionsClientComplete, FBeamRequestContext, Context, UGetSessionsClientRequest*, Request);

using FGetSessionsClientFullResponse = FBeamFullResponse<UGetSessionsClientRequest*, USessionClientHistoryResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSessionsClientFullResponse, FGetSessionsClientFullResponse);
