#include "AbilityTestCode/Attributes/UGGHealthSet.h"
#include "Misc/AutomationTest.h"


BEGIN_DEFINE_SPEC(FHealthSetSpec, "UE5_Workshop.GGHealthSetSpec",
                  EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)


END_DEFINE_SPEC(FHealthSetSpec)


void FHealthSetSpec::Define()
{
	Describe("Clamp Test for health set", [this]()
	{
		It("Test A clamp higher", [this]
		{
			return false;
		});
	});
}
