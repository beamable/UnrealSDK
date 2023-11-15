
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfObjectRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/ObjectsMetadataResponse.h"

#include "GetDataMetadataRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetDataMetadataRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Request", Category="Beam")
	FOptionalArrayOfObjectRequestBody Request = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FOptionalInt64 PlayerId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetDataMetadataRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Cloudsaving", DisplayName="Beam - Make GetDataMetadata",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Request,_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetDataMetadataRequest* Make(FOptionalArrayOfObjectRequestBody _Request, FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDataMetadataSuccess, FBeamRequestContext, Context, UGetDataMetadataRequest*, Request, UObjectsMetadataResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDataMetadataError, FBeamRequestContext, Context, UGetDataMetadataRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetDataMetadataComplete, FBeamRequestContext, Context, UGetDataMetadataRequest*, Request);

using FGetDataMetadataFullResponse = FBeamFullResponse<UGetDataMetadataRequest*, UObjectsMetadataResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetDataMetadataFullResponse, FGetDataMetadataFullResponse);
