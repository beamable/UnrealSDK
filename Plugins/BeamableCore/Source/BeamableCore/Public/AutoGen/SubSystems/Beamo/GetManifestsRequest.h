
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/GetManifestsResponse.h"

#include "GetManifestsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset")
	FOptionalInt32 Offset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived")
	FOptionalBool bArchived;

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Offset,_Limit,_bArchived,Outer"))
	static UGetManifestsRequest* MakeGetManifestsRequest(FOptionalInt32 _Offset, FOptionalInt32 _Limit, FOptionalBool _bArchived, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestsSuccess, FBeamRequestContext, Context, UGetManifestsRequest*, Request, UGetManifestsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestsError, FBeamRequestContext, Context, UGetManifestsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestsComplete, FBeamRequestContext, Context, UGetManifestsRequest*, Request);

using FGetManifestsFullResponse = FBeamFullResponse<UGetManifestsRequest*, UGetManifestsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestsFullResponse, FGetManifestsFullResponse);
