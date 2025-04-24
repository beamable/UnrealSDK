
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/GetActiveOffersResponse.h"

#include "GetOffersAdminRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetOffersAdminRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language", Category="Beam")
	FOptionalString Language = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time", Category="Beam")
	FOptionalString Time = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stores", Category="Beam")
	FOptionalString Stores = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetOffersAdminRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make GetOffersAdmin",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Language,_Time,_Stores,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetOffersAdminRequest* Make(int64 _ObjectId, FOptionalString _Language, FOptionalString _Time, FOptionalString _Stores, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOffersAdminSuccess, FBeamRequestContext, Context, UGetOffersAdminRequest*, Request, UGetActiveOffersResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetOffersAdminError, FBeamRequestContext, Context, UGetOffersAdminRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetOffersAdminComplete, FBeamRequestContext, Context, UGetOffersAdminRequest*, Request);

using FGetOffersAdminFullResponse = FBeamFullResponse<UGetOffersAdminRequest*, UGetActiveOffersResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetOffersAdminFullResponse, FGetOffersAdminFullResponse);
