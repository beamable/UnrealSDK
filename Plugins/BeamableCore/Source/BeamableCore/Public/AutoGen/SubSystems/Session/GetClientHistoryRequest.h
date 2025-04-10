
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/SessionClientHistoryResponse.h"

#include "GetClientHistoryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetClientHistoryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Month", Category="Beam")
	FOptionalInt32 Month = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Year", Category="Beam")
	FOptionalInt32 Year = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetClientHistoryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", DisplayName="Make GetClientHistory",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Month,_Year,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetClientHistoryRequest* Make(FOptionalInt32 _Month, FOptionalInt32 _Year, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientHistorySuccess, FBeamRequestContext, Context, UGetClientHistoryRequest*, Request, USessionClientHistoryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientHistoryError, FBeamRequestContext, Context, UGetClientHistoryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetClientHistoryComplete, FBeamRequestContext, Context, UGetClientHistoryRequest*, Request);

using FGetClientHistoryFullResponse = FBeamFullResponse<UGetClientHistoryRequest*, USessionClientHistoryResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetClientHistoryFullResponse, FGetClientHistoryFullResponse);
