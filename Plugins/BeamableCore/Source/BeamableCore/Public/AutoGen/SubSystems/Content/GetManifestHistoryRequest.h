
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamContentManifestId.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/GetManifestHistoryResponse.h"

#include "GetManifestHistoryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestHistoryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FOptionalBeamContentManifestId Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestHistoryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestHistory",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Id,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetManifestHistoryRequest* Make(FOptionalBeamContentManifestId _Id, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestHistorySuccess, FBeamRequestContext, Context, UGetManifestHistoryRequest*, Request, UGetManifestHistoryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestHistoryError, FBeamRequestContext, Context, UGetManifestHistoryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestHistoryComplete, FBeamRequestContext, Context, UGetManifestHistoryRequest*, Request);

using FGetManifestHistoryFullResponse = FBeamFullResponse<UGetManifestHistoryRequest*, UGetManifestHistoryResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestHistoryFullResponse, FGetManifestHistoryFullResponse);
