
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/ObjectsMetadataResponse.h"

#include "GetDataMetadataRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetDataMetadataRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Request")
	TMap<FString, FString> Request;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	FOptionalInt64 PlayerId;

	// Body Params
	

	// Beam Base Request Declaration
	UGetDataMetadataRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_PlayerId,Outer"))
	static UGetDataMetadataRequest* MakeGetDataMetadataRequest(TMap<FString, FString> _Request, FOptionalInt64 _PlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDataMetadataSuccess, FBeamRequestContext, Context, UGetDataMetadataRequest*, Request, UObjectsMetadataResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDataMetadataError, FBeamRequestContext, Context, UGetDataMetadataRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetDataMetadataComplete, FBeamRequestContext, Context, UGetDataMetadataRequest*, Request);

using FGetDataMetadataFullResponse = FBeamFullResponse<UGetDataMetadataRequest*, UObjectsMetadataResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetDataMetadataFullResponse, FGetDataMetadataFullResponse);
