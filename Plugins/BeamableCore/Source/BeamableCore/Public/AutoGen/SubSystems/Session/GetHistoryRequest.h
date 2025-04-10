
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/SessionHistoryResponse.h"

#include "GetHistoryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetHistoryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dbid", Category="Beam")
	int64 Dbid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Month", Category="Beam")
	FOptionalInt32 Month = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Year", Category="Beam")
	FOptionalInt32 Year = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetHistoryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", DisplayName="Make GetHistory",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Month,_Year,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetHistoryRequest* Make(int64 _Dbid, FOptionalInt32 _Month, FOptionalInt32 _Year, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetHistorySuccess, FBeamRequestContext, Context, UGetHistoryRequest*, Request, USessionHistoryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetHistoryError, FBeamRequestContext, Context, UGetHistoryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetHistoryComplete, FBeamRequestContext, Context, UGetHistoryRequest*, Request);

using FGetHistoryFullResponse = FBeamFullResponse<UGetHistoryRequest*, USessionHistoryResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetHistoryFullResponse, FGetHistoryFullResponse);
