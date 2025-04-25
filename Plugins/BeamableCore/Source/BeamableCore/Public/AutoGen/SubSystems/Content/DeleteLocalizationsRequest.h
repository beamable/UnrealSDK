
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/DeleteLocalizationRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteLocalizationsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteLocalizationsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UDeleteLocalizationRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteLocalizationsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make DeleteLocalizations",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteLocalizationsRequest* Make(TArray<ULocalizationQuery*> _Localizations, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLocalizationsSuccess, FBeamRequestContext, Context, UDeleteLocalizationsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLocalizationsError, FBeamRequestContext, Context, UDeleteLocalizationsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteLocalizationsComplete, FBeamRequestContext, Context, UDeleteLocalizationsRequest*, Request);

using FDeleteLocalizationsFullResponse = FBeamFullResponse<UDeleteLocalizationsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteLocalizationsFullResponse, FDeleteLocalizationsFullResponse);
