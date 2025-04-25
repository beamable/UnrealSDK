
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/BatchReadStatsResponse.h"

#include "GetClientBatchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetClientBatchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Ids", Category="Beam")
	FBeamStatsType ObjectIds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats", Category="Beam")
	FOptionalString Stats = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Format", Category="Beam")
	FOptionalString Format = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetClientBatchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make GetClientBatch",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Stats,_Format,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetClientBatchRequest* Make(FBeamStatsType _ObjectIds, FOptionalString _Stats, FOptionalString _Format, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientBatchSuccess, FBeamRequestContext, Context, UGetClientBatchRequest*, Request, UBatchReadStatsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientBatchError, FBeamRequestContext, Context, UGetClientBatchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetClientBatchComplete, FBeamRequestContext, Context, UGetClientBatchRequest*, Request);

using FGetClientBatchFullResponse = FBeamFullResponse<UGetClientBatchRequest*, UBatchReadStatsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetClientBatchFullResponse, FGetClientBatchFullResponse);
