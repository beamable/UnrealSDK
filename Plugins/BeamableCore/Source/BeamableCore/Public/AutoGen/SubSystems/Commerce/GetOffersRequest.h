
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/GetActiveOffersResponse.h"

#include "GetOffersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetOffersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language")
	FOptionalString Language;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time")
	FOptionalString Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stores")
	FOptionalString Stores;

	// Body Params
	

	// Beam Base Request Declaration
	UGetOffersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Language,_Time,_Stores,Outer"))
	static UGetOffersRequest* MakeGetOffersRequest(int64 _ObjectId, FOptionalString _Language, FOptionalString _Time, FOptionalString _Stores, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOffersSuccess, FBeamRequestContext, Context, UGetOffersRequest*, Request, UGetActiveOffersResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOffersError, FBeamRequestContext, Context, UGetOffersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetOffersComplete, FBeamRequestContext, Context, UGetOffersRequest*, Request);

using FGetOffersFullResponse = FBeamFullResponse<UGetOffersRequest*, UGetActiveOffersResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetOffersFullResponse, FGetOffersFullResponse);
